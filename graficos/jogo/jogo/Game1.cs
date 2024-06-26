using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System;
using System.Runtime.InteropServices;

namespace jogo
{
    public class Game1 : Game
    {
        private GraphicsDeviceManager _graphics;
        private SpriteBatch _spriteBatch;
        private SpriteFont _font;
        private MouseState _previousMouseState;
        private Texture2D _backgroundTexture;
        private Texture2D _loadingTexture; // Textura da tela de carregamento
        private GameState _currentGameState;
        private bool _isLoading; // Variável para controlar se a tela de carregamento está ativa
        private float _loadingTimer; // Timer para controlar o tempo de exibição da tela de carregamento
        private const float LoadingTime = 15f; // Tempo de carregamento em segundos

        // Campos específicos para a barra de carregamento animada
        private Texture2D _loadingBarBackgroundTexture; // Textura do fundo da barra de carregamento
        private Texture2D[] _loadingBarFillFrames; // Array de texturas para os frames da animação
        private float _progress; // Progresso do carregamento (de 0 a 1)
        private int _currentAnimationFrame; // Índice do frame atual da animação
        private const float AnimationSpeed = 0.1f; // Velocidade de animação da barra de carregamento

        public Game1()
        {
            _graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            IsMouseVisible = true;
        }

        protected override void Initialize()
        {
            base.Initialize();
            _currentGameState = GameState.MainMenu;
            _isLoading = false;
            _loadingTimer = 0f;
        }

        protected override void LoadContent()
        {
            _spriteBatch = new SpriteBatch(GraphicsDevice);
            _font = Content.Load<SpriteFont>("File");
            _backgroundTexture = Content.Load<Texture2D>("backgroun2");
            _loadingTexture = Content.Load<Texture2D>("carregamento"); // Carrega a textura da tela de carregamento
            _loadingBarBackgroundTexture = Content.Load<Texture2D>("barracarregamento");

            // Carrega os frames da animação
            _loadingBarFillFrames = new Texture2D[3]; // Suponha que existam 3 frames na animação
            for (int i = 0; i < _loadingBarFillFrames.Length; i++)
            {
                _loadingBarFillFrames[i] = Content.Load<Texture2D>($"loadingBarFill_{i}");
            }

            _currentAnimationFrame = 0; // Começa com o primeiro frame da animação
        }

        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
                Exit();

            MouseState currentMouseState = Mouse.GetState();

            if (_isLoading)
            {
                // Atualiza o timer da tela de carregamento
                _loadingTimer += (float)gameTime.ElapsedGameTime.TotalSeconds;

                // Simulação de progresso do carregamento (substitua com lógica real)
                _progress = Math.Min(_loadingTimer / LoadingTime, 1f);

                // Atualiza a animação da barra de carregamento
                UpdateLoadingAnimation();

                // Se o timer exceder o tempo de carregamento, muda para o estado de jogo
                if (_loadingTimer >= LoadingTime)
                {
                    _isLoading = false;
                    // Inicia o jogo na dificuldade selecionada
                    switch (_currentGameState)
                    {
                        case GameState.Playing:
                            // Inicia o jogo com a dificuldade selecionada
                            break;
                        default:
                            break;
                    }
                }
            }
            else
            {
                switch (_currentGameState)
                {
                    case GameState.MainMenu:
                        UpdateMainMenu(currentMouseState);
                        break;
                    case GameState.DifficultySelection:
                        UpdateDifficultySelection(currentMouseState);
                        break;
                    case GameState.Playing:
                        // Lógica de jogo em andamento
                        break;
                }
            }

            _previousMouseState = currentMouseState;
            base.Update(gameTime);
        }

        private void UpdateLoadingAnimation()
        {
            // Lógica para atualizar a animação da barra de carregamento
            // Exemplo simples: avança para o próximo frame com base no progresso
            _currentAnimationFrame = (int)(_progress * (_loadingBarFillFrames.Length - 1));
        }

        private void UpdateMainMenu(MouseState currentMouseState)
        {
            Rectangle enterButton = new Rectangle(GraphicsDevice.Viewport.Width / 2 - 50, GraphicsDevice.Viewport.Height / 2, 100, 30);
            Rectangle exitButton = new Rectangle(GraphicsDevice.Viewport.Width / 2 - 50, GraphicsDevice.Viewport.Height / 2 + 40, 100, 30);

            if (currentMouseState.LeftButton == ButtonState.Pressed && _previousMouseState.LeftButton == ButtonState.Released)
            {
                if (enterButton.Contains(currentMouseState.Position))
                {
                    _currentGameState = GameState.DifficultySelection;
                }
                else if (exitButton.Contains(currentMouseState.Position))
                {
                    Exit();
                }
            }
        }

        private void UpdateDifficultySelection(MouseState currentMouseState)
        {
            Rectangle easyButton = new Rectangle(GraphicsDevice.Viewport.Width / 2 - 50, GraphicsDevice.Viewport.Height / 2, 100, 30);
            Rectangle mediumButton = new Rectangle(GraphicsDevice.Viewport.Width / 2 - 50, GraphicsDevice.Viewport.Height / 2 + 40, 100, 30);
            Rectangle hardButton = new Rectangle(GraphicsDevice.Viewport.Width / 2 - 50, GraphicsDevice.Viewport.Height / 2 + 80, 100, 30);

            if (currentMouseState.LeftButton == ButtonState.Pressed && _previousMouseState.LeftButton == ButtonState.Released)
            {
                if (easyButton.Contains(currentMouseState.Position))
                {
                    // Mostra a tela de carregamento ao selecionar a dificuldade "Fácil"
                    _isLoading = true;
                    _loadingTimer = 0f;
                    // Lógica adicional para iniciar o jogo com a dificuldade fácil
                }
                else if (mediumButton.Contains(currentMouseState.Position))
                {
                    // Mostra a tela de carregamento ao selecionar a dificuldade "Médio"
                    _isLoading = true;
                    _loadingTimer = 0f;
                    // Lógica adicional para iniciar o jogo com a dificuldade média
                }
                else if (hardButton.Contains(currentMouseState.Position))
                {
                    // Mostra a tela de carregamento ao selecionar a dificuldade "Difícil"
                    _isLoading = true;
                    _loadingTimer = 0f;
                    // Lógica adicional para iniciar o jogo com a dificuldade difícil
                }
            }
        }

        protected override void Draw(GameTime gameTime)
        {
            _spriteBatch.Begin();

            // Desenha o fundo preto se estiver carregando ou durante as fases do jogo
            if (_isLoading || _currentGameState == GameState.Playing)
            {
                _spriteBatch.Draw(_backgroundTexture, new Rectangle(0, 0, GraphicsDevice.Viewport.Width, GraphicsDevice.Viewport.Height), Color.Black);
            }
            else
            {
                _spriteBatch.Draw(_backgroundTexture, new Rectangle(0, 0, GraphicsDevice.Viewport.Width, GraphicsDevice.Viewport.Height), Color.White);
            }

            switch (_currentGameState)
            {
                case GameState.MainMenu:
                    DrawMainMenu();
                    break;
                case GameState.DifficultySelection:
                    DrawDifficultySelection();
                    break;
                case GameState.Playing:
                    // Lógica de jogo aqui
                    break;
            }

            // Se estiver carregando, desenha a tela de carregamento
            if (_isLoading)
            {
                float scale = 0.4f; // Define a escala para redimensionar a textura
                Vector2 scaledSize = new Vector2(_loadingTexture.Width * scale, _loadingTexture.Height * scale);
                Vector2 position = new Vector2(
                    (GraphicsDevice.Viewport.Width - scaledSize.X) / 2,
                    (GraphicsDevice.Viewport.Height - scaledSize.Y) / 2
                );
                _spriteBatch.Draw(_loadingTexture, position, null, Color.White, 0f, Vector2.Zero, scale, SpriteEffects.None, 0f);

                // Desenha a barra de carregamento sobre a tela de carregamento
                DrawLoadingBar();
            }

            _spriteBatch.End();

            base.Draw(gameTime);
        }

        private void DrawLoadingBar()
        {
            // Posição e escala da barra de carregamento
            Vector2 position = new Vector2(100, 500); // Exemplo de posição, ajuste conforme necessário
            float scale = 1.0f; // Exemplo de escala, ajuste conforme necessário

            // Desenha o fundo da barra de carregamento
            _spriteBatch.Draw(_loadingBarBackgroundTexture, position, null, Color.White, 0f, Vector2.Zero, scale, SpriteEffects.None, 0f);

            // Desenha a parte preenchida da barra de carregamento com base na animação
            _spriteBatch.Draw(_loadingBarFillFrames[_currentAnimationFrame], position, null, Color.White, 0f, Vector2.Zero, scale, SpriteEffects.None, 0f);
        }

        private void DrawMainMenu()
        {
            string titleText = "NexusNumbers";
            Vector2 titleSize = _font.MeasureString(titleText);
            Vector2 titlePosition = new Vector2((GraphicsDevice.Viewport.Width - titleSize.X) / 2, GraphicsDevice.Viewport.Height / 4);
            _spriteBatch.DrawString(_font, titleText, titlePosition, Color.White);

            string enterText = "Entrar";
            Vector2 enterSize = _font.MeasureString(enterText);
            Vector2 enterPosition = new Vector2((GraphicsDevice.Viewport.Width - enterSize.X) / 2, GraphicsDevice.Viewport.Height / 2);
            _spriteBatch.DrawString(_font, enterText, enterPosition, Color.DeepPink);

            string exitText = "Sair";
            Vector2 exitSize = _font.MeasureString(exitText);
            Vector2 exitPosition = new Vector2((GraphicsDevice.Viewport.Width - exitSize.X) / 2, GraphicsDevice.Viewport.Height / 2 + 40);
            _spriteBatch.DrawString(_font, exitText, exitPosition, Color.White);
        }

        private void DrawDifficultySelection()
        {
            string difficultyText = "Escolha a dificuldade";
            Vector2 difficultySize = _font.MeasureString(difficultyText);
            Vector2 difficultyPosition = new Vector2((GraphicsDevice.Viewport.Width - difficultySize.X) / 2, GraphicsDevice.Viewport.Height / 4);
            _spriteBatch.DrawString(_font, difficultyText, difficultyPosition, Color.White);

            string easyText = "Facil";
            Vector2 easySize = _font.MeasureString(easyText);
            Vector2 easyPosition = new Vector2((GraphicsDevice.Viewport.Width - easySize.X) / 2, GraphicsDevice.Viewport.Height / 2);
            _spriteBatch.DrawString(_font, easyText, easyPosition, Color.Orange);

            string mediumText = "Media";
            Vector2 mediumSize = _font.MeasureString(mediumText);
            Vector2 mediumPosition = new Vector2((GraphicsDevice.Viewport.Width - mediumSize.X) / 2, GraphicsDevice.Viewport.Height / 2 + 40);
            _spriteBatch.DrawString(_font, mediumText, mediumPosition, Color.LimeGreen);

            string hardText = "Dificil";
            Vector2 hardSize = _font.MeasureString(hardText);
            Vector2 hardPosition = new Vector2((GraphicsDevice.Viewport.Width - hardSize.X) / 2, GraphicsDevice.Viewport.Height / 2 + 80);
            _spriteBatch.DrawString(_font, hardText, hardPosition, Color.Purple);
        }
    }
}
